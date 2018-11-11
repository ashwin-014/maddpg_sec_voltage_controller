import numpy as np
import gym
import tensorflow as tf
import random
from memory import ReplayMemory
import h5py
import random

import pickle

def sample_policy_action(num_actions, probs):
    """
    Sample an action from an action probability distribution output by
    the policy network.
    """
    # Subtract a tiny value from probabilities in order to avoid
    # "ValueError: sum(pvals[:-1]) > 1.0" in numpy.multinomial
    # probs = probs - 0.1 #np.finfo(np.float32).epsneg
    action_index = np.argmax(probs)

    # histogram = np.random.multinomial(1, probs)
    # action_index = int(np.nonzero(histogram)[0])
    return action_index



def build_summaries(n):
	# --------------------- old -----------------------
	# episode_reward1 = tf.Variable(0.)
	# tf.summary.scalar("Reward1",episode_reward1)
	# episode_reward2 = tf.Variable(0.)
	# tf.summary.scalar("Reward2",episode_reward2)
	# episode_reward3 = tf.Variable(0.)
	# tf.summary.scalar("Reward3",episode_reward3)
	# episode_reward4 = tf.Variable(0.)
	# tf.summary.scalar("Reward4",episode_reward4)
	# shared_episode_reward = tf.Variable(0.)
	# tf.summary.scalar("shared_Reward",shared_episode_reward)

	# num_unallocated_agent_1 = tf.Variable(0.)
	# tf.summary.scalar("num_unallocated_agent_1",num_unallocated_agent_1)
	# num_unallocated_agent_2 = tf.Variable(0.)
	# tf.summary.scalar("num_unallocated_agent_2",num_unallocated_agent_2)
	# num_unallocated_agent_3 = tf.Variable(0.)
	# tf.summary.scalar("num_unallocated_agent_3",num_unallocated_agent_3)
	# num_unallocated_agent_4 = tf.Variable(0.)
	# tf.summary.scalar("num_unallocated_agent_4",num_unallocated_agent_4)

	# summary_vars = [episode_reward1,episode_reward2,episode_reward3,episode_reward4,shared_episode_reward,num_unallocated_agent_1, num_unallocated_agent_2, num_unallocated_agent_3, num_unallocated_agent_4]
	# --------------------- old -----------------------
	
	episode_reward=[]
	num_unallocated_agent=[]

	# shared_episode_reward = tf.Variable(0.)
	# tf.summary.scalar("shared_Reward",shared_episode_reward)

	for k in range(n):
		episode_reward.append(tf.Variable(0.)) 
		tf.summary.scalar("Reward"+str(k), episode_reward[k])
		num_unallocated_agent.append(tf.Variable(0.))
		tf.summary.scalar("num_unallocated_agent"+str(k),num_unallocated_agent[k])

	summary_vars = [episode_reward,  num_unallocated_agent] # shared_episode_reward,
	summary_ops = tf.summary.merge_all()

	return summary_ops, summary_vars

def eval(sess,env,args,actors,critics,noise, last_epoch): #

	summary_ops,summary_vars = build_summaries(env.n)
	# init = tf.global_variables_initializer()
	# sess.run(init)
	writer = tf.summary.FileWriter(args['summary_dir'],sess.graph)

	for actor in actors:
		actor.update_target()
	for critic in critics:
		critic.update_target()
	
	replayMemory = ReplayMemory(int(args['buffer_size']),int(args['random_seed']))

	# for last_epoch in range(int(args['max_episodes'])):
	while (last_epoch <= int(args['max_episodes'])):
		
		s = env._get_initial_state()
		episode_reward = np.zeros((env.n,))
		shared_episode_reward = np.zeros((env.n,))

		# if ep%100==0:
		# 	for k in range(env.n):
		# 		file1 = './results/savedmodels/actor'+str(k)+'/main'+str(ep)+'.h5'
		# 		file2 = './results/savedmodels/actor'+str(k)+'/target'+str(ep)+'.h5'
		# 		file3 = './results/savedmodels/critic'+str(k)+'/main'+str(ep)+'.h5'
		# 		file4 = './results/savedmodels/critic'+str(k)+'/target'+str(ep)+'.h5'
		# 		actor = actors[k]
		# 		critic = critics[k]
		# 		actor.mainModel.save_weights(file1)
		# 		actor.targetModel.save_weights(file2)
		# 		critic.mainModel.save_weights(file3)
		# 		critic.targetModel.save_weights(file4)

		if last_epoch%100==0:
			for k in range(env.n):
				# file1 = './results/savedmodels/actor'+str(k)+'/main'+str(ep)+'.h5'
				# file2 = './results/savedmodels/actor'+str(k)+'/target'+str(ep)+'.h5'
				# file3 = './results/savedmodels/critic'+str(k)+'/main'+str(ep)+'.h5'
				# file4 = './results/savedmodels/critic'+str(k)+'/target'+str(ep)+'.h5'
				actor = actors[k]
				critic = critics[k]
				# actor.mainModel.save_weights(file1, overwrite=True)
				# actor.targetModel.save_weights(file2, overwrite=True)
				# critic.mainModel.save_weights(file3, overwrite=True)
				# critic.targetModel.save_weights(file4, overwrite=True)

				file5 = './results/savedmodels/actor'+str(k)+'/mainmodel-'+str(last_epoch)+'.h5'
				file6 = './results/savedmodels/actor'+str(k)+'/targetmodel-'+str(last_epoch)+'.h5'
				file7 = './results/savedmodels/critic'+str(k)+'/mainmodel-'+str(last_epoch)+'.h5'
				file8 = './results/savedmodels/critic'+str(k)+'/targetmodel-'+str(last_epoch)+'.h5'
				# actor = actors[k]
				# critic = critics[k]
				actor.mainModel.save(file5, overwrite=True, include_optimizer=True)
				actor.targetModel.save(file6, overwrite=True, include_optimizer=True)
				critic.mainModel.save(file7, overwrite=True, include_optimizer=True)
				critic.targetModel.save(file8, overwrite=True, include_optimizer=True)

				# with open(file5, 'wb') as file1:  
				# 	pickle.dump(actor.mainModel, file1)
				# with open(file6, 'wb') as file2:
				# 	pickle.dump(actor.targetModel, file2)
				# with open(file7, 'wb') as file3:  
				# 	pickle.dump(critic.mainModel, file3)
				# with open(file8, 'wb') as file4:
				# 	pickle.dump(critic.mainModel, file4)

		# final_alloc = np.zeros(shape=(12,4,2))
		for stp in range(int(args['max_episode_len'])):
			# if args['render_env']:
			# 	env.render()

			a = []
			
			for i in range(env.n):
				actor = actors[i]

				# ---------------------------------------- removed print -------------------------------
				# print(actor.act(np.reshape(s[i],(-1,actor.state_dim)),noise[i]()).reshape(actor.action_dim,))
				# -----------------------------------------------------------------------------------------

				# action_index = sample_policy_action(actor.action_dim, actor.act(np.reshape(s[i],(-1,actor.state_dim)),noise[i]()).reshape(actor.action_dim,))
				# a_t = np.zeros([actor.action_dim])
				# a_t[action_index] = 1
				# a.append(a_t.reshape(actor.action_dim,))

				a.append(actor.act(np.reshape(s[i],(-1,actor.state_dim)),noise[i]()).reshape(actor.action_dim,))

#  ------------------- removed eval ------------------
				# final_alloc[stp,i,:] = actor.predict_target(np.reshape(s[i],(-1,actor.state_dim)))
				# print(final_alloc[stp,i,:])
				# a.append(final_alloc[stp,i,:]) #actor.predict_target(np.reshape(s[i],(-1,actor.state_dim)))
#  ------------------- removed eval ------------------


				# a.append(actor.act(np.reshape(s[i],(-1,actor.state_dim)),noise[i]()).reshape(actor.action_dim,))
				
				# ---------------------- removed print --------------------------
				# print("Action: {}\nAlloc: {}, Num: {}".format(a[i], env.agents[i].amount_allocated, len(env.agents[i].allocated_load)))
				# ---------------------- removed print --------------------------

				
			s2,r,done,_ = env.step(a) # a is a list with each element being an array

			# for j in range(env.n):
			# 	print("\nUnalloc: {}".format(env.agents[j].deq_for_unalloc))
			
			# ----------------- shared reward --------------------------
			shared_r = np.full(shape=len(r), fill_value = np.sum(r))
			# shared_r -= np.mean(shared_r)
			# shared_r /= np.std(shared_r)
			# -------------------------------------------------------

			r -= np.mean(r)
			r /= np.std(r)

			replayMemory.add(s,a, shared_r,done,s2)
			s = s2
			action_dims_done = 0
			for i in range(env.n):
				actor = actors[i]
				critic = critics[i]
				if replayMemory.size()>int(args['minibatch_size']):

					s_batch,a_batch,r_batch,d_batch,s2_batch = replayMemory.miniBatch(int(args['minibatch_size']))
					a = []
					for j in range(env.n):
						state_batch_j = np.asarray([x for x in s_batch[:,j]]) #batch processing will be much more efficient even though reshaping will have to be done
						a.append(actors[j].predict_target(state_batch_j))
						# print(len(a))

					a_temp = np.transpose(np.asarray(a),(1,0,2))
					# print(a_temp)
					a_for_critic = np.asarray([x.flatten() for x in a_temp])
					# print(a_for_critic)
					s2_batch_i = np.asarray([x for x in s2_batch[:,i]]) # Checked till this point, should be fine.
					targetQ = critic.predict_target(s2_batch_i,a_for_critic) # Should  work, probably

					yi = []
					for k in range(int(args['minibatch_size'])):
						# print(k)
						if d_batch[:,i][k]:
							yi.append([r_batch[:,i][k],0])
						else:
							yi.append(r_batch[:,i][k] + critic.gamma*targetQ[k])
					# print(yi)
					s_batch_i = np.asarray([x for x in s_batch[:,i]])
					critic.train(s_batch_i,np.asarray([x.flatten() for x in a_batch]),np.reshape(np.array(yi),(int(args['minibatch_size']),2)))
					
					actions_pred = []
					for j in range(env.n):
						state_batch_j = np.asarray([x for x in  s2_batch[:,j]])
						actions_pred.append(actors[j].predict(state_batch_j)) # Should work till here, roughly, probably

					a_temp = np.transpose(np.asarray(actions_pred),(1,0,2))
					a_for_critic_pred = np.asarray([x.flatten() for x in a_temp])
					s_batch_i = np.asarray([x for x in s_batch[:,i]])
					grads = critic.action_gradients(s_batch_i,a_for_critic_pred)[:,action_dims_done:action_dims_done + actor.action_dim]
					actor.train(s_batch_i,grads)
					actor.update_target()
					critic.update_target()
				
				action_dims_done = action_dims_done + actor.action_dim
			episode_reward += r
			shared_episode_reward += shared_r
		
		last_epoch+=1


		# print("final alloc : ",final_alloc)
		# --------------- print removed ----------------
		# for k in range(env.n):
		# 	print("\ndeq_adl_after ep", env.agents[k].deq_adl, "\n\ndeq_unalloc", env.agents[k].deq_for_unalloc)
		# --------------- print removed ----------------

		if (last_epoch)%10==0:

# ----------------------------  Change for num agents --------------------

			for k in range(env.n):
				# feed_dict = dict(zip())
				# summary_vars = np.array(summary_vars)
				print("\n\nvars list : ", summary_vars)
				# flat_summary_vars= summary_vars.flatten()
				flat_summary_vars = [item for sublist in summary_vars for item in sublist]
				print(flat_summary_vars)
				# dictlist = list(episode_reward)#+ [shared_episode_reward[0]] # +[env.agents[k].deq_for_unalloc[j] for j in range(env.n_adl)]
				# unalloc_list = [env.agents[k].deq_for_unalloc[j] for j in range(env.n_adl)]

				# print("\n\n dictlist : ",dictlist)
				# print("\n\nunalloc list : ", unalloc_list)
				# print("\n\ncombined list : ", dictlist+ unalloc_list)
				print("\n\nprint", list(episode_reward) +[env.agents[k].deq_for_unalloc[j] for j in range(env.n_adl)])

				feed_dict = dict(zip(flat_summary_vars ,list(episode_reward) +[len(env.agents[k].deq_for_unalloc[j]) for j in range(env.n_adl)])) # [shared_episode_reward[0]]

				# summary_str = sess.run(summary_ops, feed_dict = {summary_vars[0]: episode_reward[0], summary_vars[1]: episode_reward[1], summary_vars[2]: episode_reward[2], summary_vars[3]: episode_reward[3], summary_vars[4]: shared_episode_reward[0], summary_vars[5]: len(env.agents[k].deq_for_unalloc[0]), summary_vars[6]: len(env.agents[k].deq_for_unalloc[1]), summary_vars[7]: len(env.agents[k].deq_for_unalloc[2]), summary_vars[8]: len(env.agents[k].deq_for_unalloc[3])})

				summary_str = sess.run(summary_ops, feed_dict=feed_dict)
				writer.add_summary(summary_str,last_epoch)
				writer.flush()
				#print ('|Reward: {:d}| Episode: {:d}| Qmax: {:.4f}'.format(int(episode_reward),ep,(episode_av_max_q/float(stp))))
				print("\ndeq_adl_after ep", env.agents[k].deq_adl, "\n\ndeq_unalloc", env.agents[k].deq_for_unalloc)
				print ('|Reward: {} | Shared Reward: {}	| Episode: {:d} '.format(episode_reward,shared_episode_reward,last_epoch))
			#print(done)
			if last_epoch == int(args['max_episodes']): # np.all(done):
				#summary_str = sess.run(summary_ops, feed_dict = {summary_vars[0]: episode_reward, summary_vars[1]: episode_av_max_q/float(stp)})
				summary_str = sess.run(summary_ops, feed_dict = {summary_vars[0]: episode_reward[0], summary_vars[1]: episode_reward[3]})
				writer.add_summary(summary_str,last_epoch)
				writer.flush()
				#print ('|Reward: {:d}| Episode: {:d}| Qmax: {:.4f}'.format(int(episode_reward),ep,(episode_av_max_q/float(stp))))
				print ('|Reward: {}	| Episode: {:d}'.format(episode_reward,last_epoch))
				break

			if stp == int(args['max_episode_len'])-1:
				print ('|Reward: {}	| Episode: {:d}'.format(episode_reward,last_epoch))