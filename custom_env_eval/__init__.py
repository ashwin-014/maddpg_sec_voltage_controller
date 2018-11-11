import logging
from gym.envs.registration import register

logger = logging.getLogger(__name__)

register(
    id='Multiagent-eval-v0',
    entry_point='custom_env_eval.custom_env_test_eval:MultiAgent',
)